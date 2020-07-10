// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASIC_HTTP_AUTH_H
#define BASIC_HTTP_AUTH_H

#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <unordered_set>

namespace isc {
namespace http {

/// @brief Represents a basic HTTP authentication.
///
/// It computes the credential from user and password.
class BasicHttpAuth {
public:

    /// @brief Constructor.
    ///
    /// @param user User name
    /// @param password Password
    /// @throw BadValue if user contains the ':' character.
    BasicHttpAuth(const std::string& user, const std::string& password);

    /// @brief Constructor.
    ///
    /// @param secret user:password string
    /// @throw BadValue if secret does not contain the ';' character.
    BasicHttpAuth(const std::string& secret);

    /// @brief Returns the secret.
    const std::string& getSecret() const {
        return (secret_);
    }

    /// @brief Returns the credential (base64 of the UTF-8 secret).
    const std::string& getCredential() const {
        return (credential_);
    }

private:

    /// @brief Build the secret from user and password.
    void buildSecret();

    /// @brief Build the credential from the secret.
    void buildCredential();

    /// @brief User name.
    std::string user_;

    /// @brief Password.
    std::string password_;

    /// @brief Secret.
    std::string secret_;

    /// @brief Credential.
    std::string credential_;
};

/// @brief Type of pointers to basic HTTP authentication objects.
typedef boost::shared_ptr<BasicHttpAuth> BasicHttpAuthPtr;

/// @brief Type of basic HTTP authentication credential list.
typedef std::unordered_set<std::string> BasicHttpAuthList;

/// @brief Verify if a credential is authorized.
///
/// @param credential Credential to validate.
/// @param list List of authorized credentials.
/// @return True if authorized, false otherwise.
bool allow(const std::string& credential, const BasicHttpAuthList& list);

} // end of namespace isc::http
} // end of namespace isc

#endif // endif BASIC_HTTP_AUTH_H
