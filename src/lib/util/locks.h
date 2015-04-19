// Copyright (C) 2011, 2015 Internet Systems Consortium, Inc. ("ISC")
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

/// This file (right now) provides dummy locks
/// It also contains code to use boost/threads locks:
///
///
/// All locks are dummy classes that don't actually do anything. At this moment,
/// only the very minimal set of methods that we actually use is defined.
///
/// Note that we need to include <config.h> in our .cc files for that
/// to be set.

#ifndef CONFIG_H_WAS_INCLUDED
#error "config.h must be included before but was not"
#endif

#ifndef LOCKS
#define LOCKS

#include <util/api.h>

namespace isc {
namespace util {
namespace locks {

class KEA_UTIL_API mutex {
};

class KEA_UTIL_API recursive_mutex {
};

class KEA_UTIL_API upgradable_mutex {
};

template <typename T>
class KEA_UTIL_API sharable_lock {
public:
    sharable_lock(T) {}
};

template <typename T>
class KEA_UTIL_API scoped_lock {
public:
    scoped_lock(T) {}

    // We need to define this explicitly.  Some versions of clang++ would
    // complain about this otherwise.  See Trac ticket #2340
    ~scoped_lock() {}

    void lock() {}
    void unlock() {}
};

} // namespace locks
} // namespace util
} // namespace isc

#endif // LOCKS
