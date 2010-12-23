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

// $Id$

#ifndef __COMMON_H
#define __COMMON_H 1

#include <stdexcept>
#include <string>

/// An exception class that is thrown in an unrecoverable error condition.
///
/// This exception should not be caught except at the highest level of
/// the application only for terminating the program gracefully, and so
/// it cannot be a derived class of \c isc::Exception.
class FatalError : public std::runtime_error {
public:
    FatalError(const std::string& what) : std::runtime_error(what)
    {}
};

#endif // __COMMON_H

// Local Variables:
// mode: c++
// End:
