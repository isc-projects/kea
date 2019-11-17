// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_MGR_H
#define MULTI_THREADING_MGR_H

#include <boost/noncopyable.hpp>
#include <mutex>

namespace isc {
namespace util {

/// @brief Multi Threading Manager.
///
/// This singleton class holds the multi-threading mode.
///
/// The standard way to use it is:
/// @code
/// if (MultiThreadingMgr::instance().getMode()) {
///     multi-threaded code
/// } else {
///     single-threaded code
/// }
/// @endcode
///
/// For instance for a class protected by its mutex:
/// @code
/// namespace locked {
///     int foo() { ... }
/// } // end of locked namespace
///
/// int foo() {
///     return MultiThreadingMgr::call(mutex_, []() {return locked::foo()});
/// }
/// @endcode

class MultiThreadingMgr : public boost::noncopyable {
public:

    /// @brief Returns a single instance of Multi Threading Manager.
    ///
    /// MultiThreadingMgr is a singleton and this method is the only way
    /// of accessing it.
    ///
    /// @return the single instance.
    static MultiThreadingMgr& instance();

    /// @brief Get the mode.
    ///
    /// @return the current mode: true if multi-threading is enabled,
    /// false otherwise.
    bool getMode() const;

    /// @brief Set the mode.
    ///
    /// @param enabled The new mode.
    void setMode(bool enabled);

    /// @brief Call a Functor in MT or ST mode
    ///
    /// @tparam Lockable a lock which is used to create a thread safe context
    /// @tparam Callable a functor which will be called in MT or ST mode
    /// @param lk the lock object to perform lock in MT mode
    /// @param f the functor to call
    /// @result the result of the functor call
    template<typename Lockable, typename Callable>
    static auto call(Lockable& lk, const Callable& f) {
        if (MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<Lockable> lock(lk);
            return f();
        } else {
            return f();
        }
    }

protected:

    /// @brief Constructor.
    MultiThreadingMgr();

    /// @brief Destructor.
    virtual ~MultiThreadingMgr();

private:
    /// @brief the current mode.
    bool enabled_;
};

} // namespace isc::util
} // namespace isc

#endif // MULTI_THREADING_MGR_H
