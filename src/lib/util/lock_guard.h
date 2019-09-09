// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2017-2019 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
//          Cristian Secareanu <cristian.secareanu@qualitance.com>
//          Razvan Becheriu <razvan.becheriu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LOCK_GUARD_H
#define LOCK_GUARD_H

#include <memory>

namespace isc {
namespace util {

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

}  // namespace util
}  // namespace isc

#endif  // LOCK_GUARD_H
