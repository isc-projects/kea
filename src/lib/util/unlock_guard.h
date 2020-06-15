// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNLOCK_GUARD_H
#define UNLOCK_GUARD_H

#include <boost/noncopyable.hpp>

namespace isc {
namespace util {

/// @brief Unlock Guard.
///
/// Acts as a reverse std::lock_guard.
template<typename Lock>
class UnlockGuard : public boost::noncopyable {
public:
    /// @brief Constructor.
    ///
    /// Unlock mutex object on constructor.
    explicit UnlockGuard(Lock& lock) : lock_(lock) {
        lock_.unlock();
    }

    /// @brief Destructor.
    ///
    /// Lock mutex object on destructor.
    ~UnlockGuard() {
        lock_.lock();
    }

private:
    /// @brief The mutex object.
    Lock& lock_;
};

} // namespace util
} // namespace isc

#endif // UNLOCK_GUARD_H
