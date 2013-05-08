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

#ifndef INTERPROCESS_SYNC_NULL_H
#define INTERPROCESS_SYNC_NULL_H

#include <util/interprocess_sync.h>

namespace isc {
namespace util {

/// \brief Null Interprocess Sync Class
///
/// This class specifies a concrete implementation for a null (no effect)
/// interprocess synchronization mechanism. Please see the
/// InterprocessSync class documentation for usage.
class InterprocessSyncNull : public InterprocessSync {
public:
    /// \brief Constructor
    ///
    /// Creates a null interprocess synchronization object
    ///
    /// \param task_name Name of the synchronization task. This has to be
    /// identical among the various processes that need to be
    /// synchronized for the same task.
    InterprocessSyncNull(const std::string& task_name) :
        InterprocessSync(task_name)
    {}

    /// \brief Destructor
    virtual ~InterprocessSyncNull();

protected:
    /// \brief Acquire the lock (never blocks)
    ///
    /// \return Always returns true
    bool lock();

    /// \brief Try to acquire a lock (doesn't block)
    ///
    /// \return Always returns true
    bool tryLock();

    /// \brief Release the lock
    ///
    /// \return Always returns true
    bool unlock();
};

} // namespace util
} // namespace isc

#endif // INTERPROCESS_SYNC_NULL_H
