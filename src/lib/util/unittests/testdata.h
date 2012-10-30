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

#ifndef UTIL_UNITTESTS_TESTDATA_H
#define UTIL_UNITTESTS_TESTDATA_H 1

/**
 * \file testdata.h
 * \brief Manipulating test data files.
 *
 * This utility defines functions that help test case handle test data
 * stored in a file.
 */

namespace isc {
namespace util {
namespace unittests {
/// Add a path (directory) that \c openTestData() will search for test data
/// files.
void addTestDataPath(const std::string& path);

/// Open a file specified by 'datafile' using the data paths registered via
/// addTestDataPath().  On success, ifs will be ready for reading the data
/// stored in 'datafile'.  If the data file cannot be open with any of the
/// registered paths, a runtime_error exception will be thrown.
///
/// \note Care should be taken if you want to reuse the same single \c ifs
/// for multiple input data.  Some standard C++ library implementations retain
/// the failure bit if the first stream reaches the end of the first file,
/// and make the second call to \c ifstream::open() fail.  The safest way
/// is to use a different \c ifstream object for a new call to this function;
/// alternatively make sure you explicitly clear the error bit by calling
/// \c ifstream::clear() on \c ifs.
void openTestData(const char* const datafile, std::ifstream& ifs);
}
}
}

#endif // UTIL_UNITTESTS_TESTDATA_H

// Local Variables:
// mode: c++
// End:
