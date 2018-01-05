// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    return (toText() < url.toText());
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

    std::ostringstream e;

    // Retrieve scheme
    size_t p = url_.find(":");
    if ((p == 0) || (p == std::string::npos)) {
        e << "url " << url_ << " lacks http or https scheme";
        error_message_ = e.str();
        return;
    }

    // Validate scheme.
    std::string scheme = url_.substr(0, p);
    if (scheme == "http") {
        scheme_ = Url::HTTP;

    } else if (scheme == "https") {
        scheme_ = Url::HTTPS;

    } else {
        e << "invalid scheme " << scheme << " in " << url_;
        error_message_ = e.str();
        return;
    }

    // Colon and two slashes should follow the scheme
    if (url_.substr(p, 3) != "://") {
        e << "expected :// after scheme in " << url_;
        error_message_ = e.str();
        return;
    }

    // Move forward to hostname.
    p += 3;
    if (p >= url_.length()) {
        e << "hostname missing in " << url_;
        error_message_ = e.str();
        return;
    }

    size_t h = 0;

    // IPv6 address is specified within [ ].
    if (url_.at(p) == '[') {
        h = url_.find(']', p);
        if (h == std::string::npos) {
            e << "expected ] after IPv6 address in " << url_;
            error_message_ = e.str();
            return;

        } else if (h == p + 1) {
            e << "expected IPv6 address within [] in " << url_;
            error_message_ = e.str();
            return;
        }

        // Move one character beyond the ].
        ++h;

    } else {
        // There is a normal hostname or IPv4 address. It is terminated
        // by the colon (for port number), a slash (if no port number) or
        // goes up to the end of the URL.
        h = url_.find(":", p);
        if (h == std::string::npos) {
            h = url_.find("/", p);
            if (h == std::string::npos) {
                // No port number and no slash.
                h = url_.length();
            }
        }
    }

    // Extract the hostname.
    hostname_ = url_.substr(p, h - p);

    // If there is no port number and no path, simply return and mark the
    // URL as valid.
    if (h == url_.length()) {
        valid_ = true;
        return;
    }

    // If there is a port number, we need to read it and convert to
    // numeric value.
    if (url_.at(h) == ':') {
        if (h == url_.length() - 1) {
            e << "expected port number after : in " << url_;
            error_message_ = e.str();
            return;
        }
        // Move to the port number.
        ++h;

        // Port number may be terminated by a slash or by the end of URL.
        size_t s = url_.find('/', h);
        std::string port_str;
        if (s == std::string::npos) {
            port_str = url_.substr(h);
        } else {
            port_str = url_.substr(h, s - h);
        }

        try {
            // Try to convert the port number to numeric value.
            port_ = boost::lexical_cast<unsigned>(port_str);

        } catch (...) {
            e << "invalid port number " << port_str << " in " << url_;
            error_message_ = e.str();
            return;
        }

        // Go to the end of the port section.
        h = s;
    }

    // If there is anything left in the URL, we consider it a path.
    if (h != std::string::npos) {
        path_ = url_.substr(h);
    }

    valid_ = true;
}

} // end of namespace isc::http
} // end of namespace isc
