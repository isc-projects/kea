// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __UTIL_UNITTESTS_WIREDATA_H
#define __UTIL_UNITTESTS_WIREDATA_H 1

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

#endif // __UTIL_UNITTESTS_WIREDATA_H

// Local Variables:
// mode: c++
// End:
