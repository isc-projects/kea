// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <http/url.h>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include <iostream>

namespace isc {
namespace http {

Url::Url(const std::string& url)
    : url_(url), valid_(false), error_message_(), scheme_(Url::HTTPS),
      hostname_(), port_(0), path_() {
    parse();
}

bool
Url::operator<(const Url& url) const {
    return (url_ < url.rawUrl());
}

Url::Scheme
Url::getScheme() const {
    checkValid();
    return (scheme_);
}

std::string
Url::getHostname() const {
    checkValid();
    return (hostname_);
}

std::string
Url::getStrippedHostname() const {
    std::string hostname = getHostname();
    if ((hostname.length() >= 2) && (hostname.at(0) == '[')) {
        return (hostname.substr(1, hostname.length() - 2));
    }

    return (hostname);
}

unsigned
Url::getPort() const {
    checkValid();
    return (port_);
}

std::string
Url::getPath() const {
    checkValid();
    return (path_);
}

std::string
Url::toText() const {
    std::ostringstream s;
    s << (getScheme() == HTTP ? "http" : "https");
    s << "://" << getHostname();

    if (getPort() != 0) {
        s << ":" << getPort();
    }

    s << getPath();

    return (s.str());
}

void
Url::checkValid() const {
    if (!isValid()) {
        isc_throw(InvalidOperation, "invalid URL " << url_ << ": " << error_message_);
    }
}

void
Url::parse() {
    valid_ = false;
    error_message_.clear();
    scheme_ = Url::HTTPS;
    hostname_.clear();
    port_ = 0;
    path_.clear();

    std::ostringstream error;

    // Retrieve scheme
    size_t offset = url_.find(":");
    if ((offset == 0) || (offset == std::string::npos)) {
        error << "url " << url_ << " lacks http or https scheme";
        error_message_ = error.str();
        return;
    }

    // Validate scheme.
    std::string scheme = url_.substr(0, offset);
    if (scheme == "http") {
        scheme_ = Url::HTTP;

    } else if (scheme == "https") {
        scheme_ = Url::HTTPS;

    } else {
        error << "invalid scheme " << scheme << " in " << url_;
        error_message_ = error.str();
        return;
    }

    // Colon and two slashes should follow the scheme
    if (url_.substr(offset, 3) != "://") {
        error << "expected :// after scheme in " << url_;
        error_message_ = error.str();
        return;
    }

    // Move forward to hostname.
    offset += 3;
    if (offset >= url_.length()) {
        error << "hostname missing in " << url_;
        error_message_ = error.str();
        return;
    }

    size_t offset2 = 0;

    // IPv6 address is specified within [ ].
    if (url_.at(offset) == '[') {
        offset2 = url_.find(']', offset);
        if (offset2 == std::string::npos) {
            error << "expected ] after IPv6 address in " << url_;
            error_message_ = error.str();
            return;

        } else if (offset2 == offset + 1) {
            error << "expected IPv6 address within [] in " << url_;
            error_message_ = error.str();
            return;
        }

        // Move one character beyond the ].
        ++offset2;

    } else {
        // There is a normal hostname or IPv4 address. It is terminated
        // by the colon (for port number), a slash (if no port number) or
        // goes up to the end of the URL.
        offset2 = url_.find(":", offset);
        if (offset2 == std::string::npos) {
            offset2 = url_.find("/", offset);
            if (offset2 == std::string::npos) {
                // No port number and no slash.
                offset2 = url_.length();
            }
        }
    }

    // Extract the hostname.
    hostname_ = url_.substr(offset, offset2 - offset);

    // If there is no port number and no path, simply return and mark the
    // URL as valid.
    if (offset2 == url_.length()) {
        valid_ = true;
        return;
    }

    // If there is a port number, we need to read it and convert to
    // numeric value.
    if (url_.at(offset2) == ':') {
        if (offset2 == url_.length() - 1) {
            error << "expected port number after : in " << url_;
            error_message_ = error.str();
            return;
        }
        // Move to the port number.
        ++offset2;

        // Port number may be terminated by a slash or by the end of URL.
        size_t slash_offset = url_.find('/', offset2);
        std::string port_str;
        if (slash_offset == std::string::npos) {
            port_str = url_.substr(offset2);
        } else {
            port_str = url_.substr(offset2, slash_offset - offset2);
        }

        try {
            // Try to convert the port number to numeric value.
            port_ = boost::lexical_cast<unsigned>(port_str);

        } catch (...) {
            error << "invalid port number " << port_str << " in " << url_;
            error_message_ = error.str();
            return;
        }

        // Go to the end of the port section.
        offset2 = slash_offset;
    }

    // If there is anything left in the URL, we consider it a path.
    if (offset2 != std::string::npos) {
        path_ = url_.substr(offset2);
        if (path_.empty()) {
            path_ = "/";
        }
    }

    valid_ = true;
}

} // end of namespace isc::http
} // end of namespace isc
