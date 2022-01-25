// Copyright (C) 2020-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_AUTH_CONFIG_H
#define HTTP_AUTH_CONFIG_H

#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <cc/user_context.h>
#include <http/request.h>
#include <http/response_creator.h>
#include <http/response_json.h>

namespace isc {
namespace http {

/// @brief Base type of HTTP authentication configuration.
class HttpAuthConfig : public isc::data::UserContext,
                       public isc::data::CfgToElement {
public:

    /// @brief Destructor.
    virtual ~HttpAuthConfig() { }

    /// @brief Set the realm.
    ///
    /// @param realm New realm.
    void setRealm(const std::string& realm) {
        realm_ = realm;
    }

    /// @brief Returns the realm.
    ///
    /// @return The HTTP authentication realm.
    const std::string& getRealm() const {
        return (realm_);
    }

    /// @brief Set the common part for file paths (usually a directory).
    ///
    /// @param directory New directory.
    void setDirectory(const std::string& directory) {
        directory_ = directory;
    }

    /// @brief Returns the common part for file paths (usually a directory).
    ///
    /// @return The common part for file paths (usually a directory).
    const std::string& getDirectory() const {
        return (directory_);
    }

    /// @brief Empty predicate.
    ///
    /// @return true if the configuration is empty so authentication
    /// is not required.
    virtual bool empty() const = 0;

    /// @brief Clear configuration.
    virtual void clear() = 0;

    /// @brief Parses HTTP authentication configuration.
    ///
    /// @param config Element holding the basic HTTP authentication
    /// configuration to be parsed.
    /// @throw DhcpConfigError when the configuration is invalid.
    virtual void parse(const isc::data::ConstElementPtr& config) = 0;

    /// @brief Unparses HTTP authentication configuration.
    ///
    /// @return A pointer to unparsed HTTP authentication configuration.
    virtual isc::data::ElementPtr toElement() const = 0;

    /// @brief Validate HTTP request.
    ///
    /// @param creator The HTTP response creator.
    /// @param request The HTTP request to validate.
    /// @return Error HTTP response if validation failed, null otherwise.
    virtual isc::http::HttpResponseJsonPtr
    checkAuth(const isc::http::HttpResponseCreator& creator,
              const isc::http::HttpRequestPtr& request) const = 0;

private:

    /// @brief The realm.
    std::string realm_;

    /// @brief Common part for file paths (usually a directory).
    std::string directory_;
};

/// @brief Type of shared pointers to HTTP authentication configuration.
typedef boost::shared_ptr<HttpAuthConfig> HttpAuthConfigPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif // endif HTTP_AUTH_CONFIG_H
