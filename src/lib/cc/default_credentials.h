// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DEFAULT_CREDENTIALS_H
#define DEFAULT_CREDENTIALS_H

#include <exceptions/exceptions.h>
#include <unordered_set>
#include <string>

namespace isc {
namespace data {

/// @brief Exception thrown on attempt to use a default credential.
class DefaultCredential : public Exception {
public:
    DefaultCredential(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { }
};

/// @brief Base class for default credentials.
struct DefaultCredentials {
    /// @brief Default credentials.
    static const std::unordered_set<std::string> DEFAULT_CREDENTIALS;

    /// @brief Check if the value is a default credential.
    ///
    /// @param value The value to check.
    /// @throw DefaultCredential if the value is in default credentials.
    static void check(const std::string& value);
};

} // end of isc::dhcp namespace
} // end of isc namespace


#endif // DEFAULT_CREDENTIALS_H
