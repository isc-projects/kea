// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_MGR_H
#define MULTI_THREADING_MGR_H

#include <boost/noncopyable.hpp>

namespace isc {
namespace util {

/// @file multi_threading_mgr.h Multi Threading Manager.
///
/// This singleton class holds the multi-threading mode.
///
/// It is split into two classes to hide the setMode method from the
/// instance static method.
///
/// The standard way to use it is:
/// @code
/// if (MultiThreadingMgr::instance().getMode) {
///     multi-threaded code
/// } else {
///     single-threaded code
/// }
/// @endcode
///
/// For instance for a class protected by its mutex:
/// @code
/// namespace locked {
///     void foo() { ... }
/// } // end of locked namespace
///
/// void foo() {
///     if (MultiThreadingMgr::instance().getMode) {
///         lock_guard<mutex> lock(mutex_);
///         locked::foo();
///     } else {
///         locked::foo();
///     }
/// }
/// @endcode

/// @brief The base class hiding the setter.
class BaseMultiThreadingMgr : public boost::noncopyable {
public:

    /// @brief Get the mode.
    ///
    /// @return the current mode: true if multi-threading is enabled,
    /// false otherwise.
    bool getMode() const;

protected:

    /// @brief Constructor.
    BaseMultiThreadingMgr();

    /// @brief Destructor.
    virtual ~BaseMultiThreadingMgr();

    /// @brief Set the mode.
    ///
    /// @param mode The new mode.
    void setMode(bool enabled);

private:
    /// @brief the current mode.
    bool enabled_;
};

/// @brief The class providing instance and setter.
class MultiThreadingMgr : public BaseMultiThreadingMgr {
public:

    /// @brief Returns a single instance of Multi Threading Manager.
    ///
    /// MultiThreadingMgr is a singleton and this method is the only way
    /// of accessing it.
    ///
    /// @return the single instance.
    static BaseMultiThreadingMgr& instance();

    using BaseMultiThreadingMgr::setMode;

protected:
    /// @brief Constructor.
    MultiThreadingMgr();

    /// @brief Destructor.
    virtual ~MultiThreadingMgr();
};

} // namespace isc::dhcp
} // namespace isc

#endif // MULTI_THREADING_MGR_H
