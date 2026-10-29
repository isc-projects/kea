// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RBAC_CONFIG_H
#define RBAC_CONFIG_H

#include <cc/simple_parser.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace rbac {

/// @brief RBAC Configuration class.
class Config {
public:
    /// @brief Constructor.
    Config() : api_files_(""), require_tls_(false) {
    }

    /// @brief Configuration parameters.
    static const data::SimpleKeywords RBAC_PARAMETERS;

    /// @brief Configuration required parameters.
    static const data::SimpleRequiredKeywords RBAC_REQUIRED_PARAMETERS;

    /// @brief Initialization.
    void init();

    /// @brief Parse the configuration.
    ///
    /// @param cfg Configuration element.
    static void parse(data::ConstElementPtr cfg);

    /// @brief Get the directory where to find API files.
    ///
    /// @return the directory where to find API files.
    const std::string& getApiFiles() const {
        return (api_files_);
    }

    /// @brief Set the directory where to find API files.
    ///
    /// @param api_files The directory where to find API files.
    void setApiFiles(const std::string& api_files) {
        api_files_ = api_files;
    }

    /// @brief Get require TLS flag.
    ///
    /// @return require TLS flag value.
    bool getRequireTls() const {
        return (require_tls_);
    }

    /// @brief Set require TLS flag.
    ///
    /// @param require_tls Require TLS flag.
    void setRequireTls(bool require_tls) {
        require_tls_ = require_tls;
    }

private:
    /// @brief The directory where to find API files.
    /// Default could be "$datadir/kea/api".
    std::string api_files_;

    /// @brief The require TLS flag.
    /// Default is false but changed to true for subject and issuer.
    bool require_tls_;
};

/// @brief The configuration.
extern Config rbacConfig;

} // end of namespace rbac
} // end of namespace isc
#endif
