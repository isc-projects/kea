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

/// This file (right now) provides dummy locks
/// It also contains code to use boost/threads locks:
///
/// if USE_BOOST_THREADS is defined, we typedef the relevant classes
/// and derive from the relevant templates so our dummy locks are
/// replaced by the boost locks (--enable-boost-threads)
///
/// If USE_BOOST_THREADS is NOT defined, all locks are dummy classes
/// that don't actually do anything. At this moment, only the very
/// minimal set of methods that we actually use is defined.
///
/// Note that we need to include <config.h> in our .cc files for that
/// to be set. we might want to enfore this at compile time with a check
/// (TODO)
/// Note that this also contains a workaround for Sunstudio; which
/// probably won't completely work right now (that is, if the TODO
/// above is completed), since that would also require some changes
/// in most (at first glance unrelated) Makefiles
/// (TODO2)

#ifndef __LOCKS_
#define __LOCKS_

#ifndef USE_BOOST_THREADS

namespace isc {
namespace locks {

class mutex {
};

class recursive_mutex {
};

class upgradable_mutex {
};

template <typename T>
class sharable_lock {
public:
    sharable_lock(T) { }
};

template <typename T>
class scoped_lock {
public:
    scoped_lock(T) { }

    void lock() {}
    void unlock() {}
};

}
}

#else // USE_BOOST_THREADS

// Workaround for a problem with boost and sunstudio 5.10
// There is a version check in there that appears wrong,
// which makes including boost/thread.hpp fail
// This will probably be fixed in a future version of boost,
// in which case this part can be removed then
#ifdef NEED_SUNPRO_WORKAROUND
#if defined(__SUNPRO_CC) && __SUNPRO_CC == 0x5100
#undef __SUNPRO_CC
#define __SUNPRO_CC 0x5090
#endif
#endif // NEED_SUNPRO_WORKAROUND

#include <boost/thread.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>

namespace isc {
namespace locks {

typedef boost::mutex mutex;
typedef boost::interprocess::interprocess_upgradable_mutex upgradable_mutex;
typedef boost::interprocess::interprocess_recursive_mutex recursive_mutex;

template <typename T>
struct sharable_lock : public boost::interprocess::sharable_lock<T> {
public:
    sharable_lock(T&  mtype) : boost::interprocess::sharable_lock<T>(mtype) {}
};


template <class T>
struct scoped_lock : public boost::interprocess::scoped_lock<T> {
public:
    scoped_lock(T& mtype) : boost::interprocess::scoped_lock<T>(mtype) { }
};

}
}


#endif // USE_BOOST_THREADS

#endif // __LOCKS_
