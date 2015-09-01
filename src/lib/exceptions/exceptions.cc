// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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
