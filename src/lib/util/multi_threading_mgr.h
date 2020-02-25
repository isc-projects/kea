// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_MGR_H
#define MULTI_THREADING_MGR_H

#include <util/thread_pool.h>

#include <boost/noncopyable.hpp>

#include <stdint.h>

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
///     void foo() { ... }
/// } // end of locked namespace
///
/// void foo() {
///     if (MultiThreadingMgr::instance().getMode()) {
///         lock_guard<mutex> lock(mutex_);
///         locked::foo();
///     } else {
///         locked::foo();
///     }
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

    /// @brief Get the packet thread pool.
    ///
    /// @return The packet thread pool of this binary instance.
    ThreadPool<std::function<void()>>& getPktThreadPool();

    /// @brief Get the configured packet thread pool size.
    ///
    /// @return The packet thread pool size of this binary instance.
    uint32_t getPktThreadPoolSize() const;

    /// @brief Set the configured packet thread pool size.
    ///
    /// @param size The packet thread pool size of this binary instance.
    void setPktThreadPoolSize(uint32_t size);

    /// @brief The system current supported hardware concurrency thread count.
    ///
    /// This function will return 0 if the value can not be determined.
    ///
    /// @return The thread count.
    static uint32_t supportedThreadCount();

    /// @brief Apply the multi-threading related settings
    ///
    /// @param enabled The enabled flag: true if multi-threading is enabled,
    /// false otherwise.
    /// @param thread_count The number of desired threads: non 0 if explicitly
    /// configured, 0 if auto scaling is desired
    void apply(bool enabled, uint32_t thread_count);

protected:

    /// @brief Constructor.
    MultiThreadingMgr();

    /// @brief Destructor.
    virtual ~MultiThreadingMgr();

private:

    /// @brief The current mode.
    bool enabled_;

    /// @brief The configured size of the packet thread pool.
    uint32_t pkt_thread_pool_size_;

    /// @brief Packet processing thread pool.
    ThreadPool<std::function<void()>> pkt_thread_pool_;
};

}  // namespace util
}  // namespace isc

#endif // MULTI_THREADING_MGR_H
