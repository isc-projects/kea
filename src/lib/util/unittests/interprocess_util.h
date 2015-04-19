// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <util/unittests/api.h>

namespace isc {
namespace util {
namespace unittests {
/// \brief A helper utility for a simple synchronization with another process.
///
/// It waits for incoming data on a given file descriptor up to 5 seconds
/// (arbitrary choice), read one byte data, and return it to the caller.
/// On any failure it returns 0xff (255), so the sender process should use
/// a different value to pass.
KEA_UTIL_UNITTESTS_API unsigned char parentReadState(int fd);
}
}
}

// Local Variables:
// mode: c++
// End:
