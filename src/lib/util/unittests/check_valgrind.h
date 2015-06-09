// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

//
// If we have the valgrind headers available, we can detect whether
// valgrind is running. This should normally never be done, as you
// want the to test the actual code in operation with valgrind.
//
// However, there is a limited set of operations where we want to
// skip some tests if run under valgrind, most notably the
// EXPECT_DEATH tests, as these would report memory leaks by
// definition.
//
// If the valgrind headers are NOT available, the method checkValgrind()
// always returns false; i.e. it always pretends the program is run
// natively
//

#ifndef UTIL_UNITTESTS_CHECK_VALGRIND_H
#define UTIL_UNITTESTS_CHECK_VALGRIND_H 1

namespace isc {
namespace util {
namespace unittests {

/// \brief Check if the program is run in valgrind
///
/// This is used to check for valgrind and skip (parts of) tests that fork,
/// such as death tests, and general forking tests, and some threading tests;
/// These tend to cause valgrind to report errors, which would hide other
/// potential valgrind reports.
///
/// \return true if valgrind headers are available, and valgrind is running,
///         false if the headers are not available, or if valgrind is not
///         running
bool runningOnValgrind();

} // end namespace unittests
} // end namespace util
} // end namespace isc

#endif // UTIL_UNITTESTS_CHECK_VALGRIND_H
