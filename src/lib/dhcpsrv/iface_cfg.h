// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef IFACE_CFG_H
#define IFACE_CFG_H

#include <set>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when duplicated interface names specified.
class DuplicateIfaceName : public Exception {
public:
    DuplicateIfaceName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when specified interface name is invalid.
class InvalidIfaceName : public Exception {
public:
    InvalidIfaceName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when specified interface doesn't exist in a system.
class NoSuchIface : public Exception {
public:
    NoSuchIface(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class IfaceCfg {
public:
    static const char* ALL_IFACES_KEYWORD;

    enum Family {
        V4, V6
    };

    IfaceCfg(Family family);

    void closeSockets();

    Family getFamily() const {
        return (family_);
    }

    void openSockets(const uint16_t port);

    void use(const std::string& iface_name);

private:

    void setState(const bool inactive);

    Family family_;
    typedef std::set<std::string> IfaceSet;
    IfaceSet iface_set_;
    bool wildcard_used_;
};

}
}

#endif // IFACE_CFG_H
