// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
