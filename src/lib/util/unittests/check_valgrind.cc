// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

namespace isc {
namespace util {
namespace unittests {

#if HAVE_VALGRIND_HEADERS
#include <valgrind/valgrind.h>
/// \brief Check if the program is run in valgrind
///
/// \return true if valgrind headers are available, and valgrind is running,
///         false if the headers are not available, or if valgrind is not
///         running
bool
runningOnValgrind() {
    return (RUNNING_ON_VALGRIND != 0);
}
#else
bool
runningOnValgrind() {
    return (false);
}
#endif // HAVE_VALGRIND_HEADERS

} // end of namespace unittests
} // end of namespace util
} // end of namespace isc
