// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <sstream>
#include <exceptions/exceptions.h>

using isc::Exception;

namespace isc {

Exception::Exception(const char* file, size_t line, const char* what)
: file_(file), line_(line), what_(what) {
    std::stringstream location;
    location << what_ << "[" << file_ << ":" << line_ << "]";
    verbose_what_ = location.str();
}

Exception::Exception(const char* file, size_t line, const std::string& what)
    : file_(file), line_(line), what_(what) {
    std::stringstream location;
    location << what_ << "[" << file_ << ":" << line_ << "]";
    verbose_what_ = location.str();
}

const char*
Exception::what() const throw() {
    return (what(false));
}

const char*
Exception::what(bool verbose) const throw() {

    // Even though it's very unlikely that c_str() throws an exception,
    // it's still not 100% guaranteed.  To meet the exception specification
    // of this function, we catch any unexpected exception and fall back to
    // the pre-defined constant.
    try {
        if (verbose) {
            return (verbose_what_.c_str());
        } else {
            return (what_.c_str());
        }
    } catch (...) {
        // no exception handling is necessary.  just have to catch exceptions.
    }
    return ("isc::Exception");
}

}
