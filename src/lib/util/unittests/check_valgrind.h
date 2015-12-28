// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
