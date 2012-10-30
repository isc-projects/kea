// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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



#ifndef RUN_ALL_H
#define RUN_ALL_H

// Avoid need for user to include this header file.

#include <gtest/gtest.h>

namespace isc {
namespace util {
namespace unittests {

/// \brief Run All Tests
///
/// A wrapper for the Google Test RUN_ALL_TESTS() macro, this calls the macro
/// but wraps the call in a try...catch block if the environment variable
/// B10TEST_CATCH_EXCEPTION is defined, and calls the macro directly if not.
///
/// The catch block catches exceptions of types isc::Exception and
/// std::exception and prints some information about them to stderr. (In the
/// case of isc::Exception, this includes the file and line number from which
/// the exception was raised.)  It then re-throws the exception.
///
/// See: https://lists.isc.org/pipermail/bind10-dev/2011-January/001867.html
/// for some context.
///
/// \return Return value from RUN_ALL_TESTS().

int run_all();

} // namespace unittests
} // namespace util
} // namespace isc



#endif // RUN_ALL_H
