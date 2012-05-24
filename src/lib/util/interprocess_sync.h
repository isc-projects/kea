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

#ifndef __INTERPROCESS_SYNC_H__
#define __INTERPROCESS_SYNC_H__

#include <string>

namespace isc {
namespace util {

class InterprocessSyncLocker;

class InterprocessSync {
friend class InterprocessSyncLocker;
public:
    /// \brief Constructor
    ///
    /// Creates a interprocess synchronization object
    InterprocessSync(const std::string& component_name) :
        component_name_(component_name), is_locked_(false)
    {}

    /// \brief Destructor
    virtual ~InterprocessSync() {}

protected:
    virtual bool lock() = 0;
    virtual bool tryLock() = 0;
    virtual bool unlock() = 0;

    const std::string component_name_;
    bool is_locked_;
};

class InterprocessSyncLocker {
public:
    InterprocessSyncLocker(InterprocessSync& sync) :
        sync_(sync)
    {}

    /// \brief Destructor
    ~InterprocessSyncLocker() {
        unlock();
    }

    bool lock() {
        return (sync_.lock());
    }

    bool tryLock() {
        return (sync_.tryLock());
    }

    bool unlock() {
        return (sync_.unlock());
    }

protected:
    InterprocessSync& sync_;
};

} // namespace util
} // namespace isc

#endif // __INTERPROCESS_SYNC_H__
