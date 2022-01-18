// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_URL_H
#define KEA_URL_H

#include <asiolink/io_address.h>
#include <string>

namespace isc {
namespace http {

/// @brief Represents an URL.
///
/// It parses the provided URL and allows for retrieving the parts
/// of it after parsing.
class Url {
public:

    /// @brief Scheme: https or http.
    enum Scheme {
        HTTP,
        HTTPS
    };

    /// @brief Constructor.
    ///
    /// Parses provided URL.
    ///
    /// @param url URL.
    explicit Url(const std::string& url);

    /// @brief compares URLs lexically.
    ///
    /// Both URLs are compared as text.
    ///
    /// @param url URL to be compared with
    /// @return true if the other operator is larger (in lexical sense)
    bool operator<(const Url& url) const;

    /// @brief Checks if the URL is valid.
    ///
    /// @return true if the URL is valid, false otherwise.
    bool isValid() const {
        return (valid_);
    }

    /// @brief Returns parsing error message.
    std::string getErrorMessage() const {
        return (error_message_);
    }

    /// @brief Returns parsed scheme.
    ///
    /// @throw InvalidOperation if URL is invalid.
    Scheme getScheme() const;

    /// @brief Returns hostname stripped from [ ] characters surrounding
    /// IPv6 address.
    ///
    /// @throw InvalidOperation if URL is invalid.
    std::string getStrippedHostname() const;

    /// @brief Returns port number.
    ///
    /// @return Port number or 0 if URL doesn't contain port number.
    /// @throw InvalidOperation if URL is invalid.
    unsigned getPort() const;

    /// @brief Returns path.
    ///
    /// @return URL path
    /// @throw InvalidOperation if URL is invalid.
    std::string getPath() const;

    /// @brief Returns textual representation of the URL.
    ///
    /// @return Text version of the URL.
    std::string toText() const;

    /// @brief Returns the raw, unparsed URL string.
    ///
    /// @return Unparsed URL string.
    const std::string& rawUrl() const {
        return (url_);
    }

private:
    /// @brief Returns hostname.
    ///
    /// @throw InvalidOperation if URL is invalid.
    std::string getHostname() const;

    /// @brief Returns boolean value indicating if the URL is valid.
    void checkValid() const;

    /// @brief Parses URL.
    ///
    /// This method doesn't throw an exception. Call @c isValid to see
    /// if the URL is valid.
    void parse();

    /// @brief Holds specified URL.
    std::string url_;

    /// @brief A flag indicating if the URL is valid.
    bool valid_;

    /// @brief Holds error message after parsing.
    std::string error_message_;

    /// @brief Parsed scheme.
    Scheme scheme_;

    /// @brief Parsed hostname.
    std::string hostname_;

    /// @brief Parsed port number.
    unsigned port_;

    /// @brief Parsed path.
    std::string path_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif // endif
