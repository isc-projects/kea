// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOCK_GUARD_H
#define LOCK_GUARD_H

#include <memory>

namespace isc {
namespace util {
namespace thread {

template <typename Lock>
class LockGuard {
public:
    LockGuard(Lock* lock) : lk_(lock) {
        if (lk_) {
            lk_->lock();
        }
    }

    ~LockGuard() {
        if (lk_) {
            lk_->unlock();
        }
    }

    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;

    LockGuard(LockGuard&&) = delete;
    LockGuard& operator=(LockGuard&&) = delete;

private:
    Lock* lk_;
};

}  // namespace thread
}  // namespace util
}  // namespace isc

#endif  // LOCK_GUARD_H
