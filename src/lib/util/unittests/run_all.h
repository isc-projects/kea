// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.



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
/// KEATEST_CATCH_EXCEPTION is defined, and calls the macro directly if not.
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
