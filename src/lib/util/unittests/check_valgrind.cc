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
