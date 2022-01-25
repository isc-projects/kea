// Copyright (C) 2020-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASIC_HTTP_AUTH_H
#define BASIC_HTTP_AUTH_H

#include <http/header_context.h>
#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
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
    /// @param user User id
    /// @param password Password
    /// @throw BadValue if user contains the ':' character.
    BasicHttpAuth(const std::string& user, const std::string& password);

    /// @brief Constructor.
    ///
    /// @param secret user:password string
    /// @throw BadValue if secret does not contain the ':' character.
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

    /// @brief User id e.g. johndoe.
    std::string user_;

    /// @brief Password e.g. secret1.
    std::string password_;

    /// @brief Secret e.g. johndoe:secret1.
    std::string secret_;

    /// @brief Credential: base64 encoding of UTF-8 secret,
    /// e.g. am9obmRvZTpzZWNyZXQx.
    std::string credential_;
};

/// @brief Type of pointers to basic HTTP authentication objects.
typedef boost::shared_ptr<BasicHttpAuth> BasicHttpAuthPtr;

/// @brief Represents basic HTTP authentication header.
struct BasicAuthHttpHeaderContext : public HttpHeaderContext {

    /// @brief Constructor.
    ///
    /// @param basic_auth Basic HTTP authentication object.
    explicit BasicAuthHttpHeaderContext(const BasicHttpAuth& basic_auth)
        : HttpHeaderContext("Authorization",
                            "Basic " + basic_auth.getCredential()) {
    }
};

} // end of namespace isc::http
} // end of namespace isc

#endif // endif BASIC_HTTP_AUTH_H
