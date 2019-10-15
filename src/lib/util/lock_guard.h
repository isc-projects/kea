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
