// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UTIL_UNITTESTS_WIREDATA_H
#define UTIL_UNITTESTS_WIREDATA_H 1

#include <cstddef>

/// \file wiredata.h
/// \brief Utilities for tests with wire data.
///
/// This utility provides convenient helper functions for unit tests using
/// wire (binary) data.

namespace isc {
namespace util {
namespace unittests {

/// \brief Compare two sets of binary data in a google test.
///
/// This method checks if the expected and actual data have the same length
/// and all bytes are the same.  If not, it reports the point of mismatch in
/// the google test format.
void matchWireData(const void* expected_data, std::size_t expected_len,
                   const void* actual_data, std::size_t actual_len);
}
}
}

#endif // UTIL_UNITTESTS_WIREDATA_H

// Local Variables:
// mode: c++
// End:
