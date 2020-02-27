// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_UTIL_H
#define MULTI_THREADING_UTIL_H

#include <boost/noncopyable.hpp>

namespace isc {
namespace dhcp {

/// @note: everything here MUST be used ONLY from the main thread.
/// When called from a thread of the pool it can deadlock.

/// @brief RAII class creating a critical section.
///
/// @note: the multi-threading mode MUST NOT be changed in the RAII
/// @c MultiThreadingCriticalSection body.
/// @note: starting and stopping the packet thread pool should be handled
/// in the main thread, if done on one of the processing threads will cause a
/// deadlock
/// This is mainly useful in hook commands which handle configuration
/// changes.
class MultiThreadingCriticalSection : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// Entering the critical section. The packet thread pool instance will be
    /// stopped so that configuration changes can be safely applied.
    MultiThreadingCriticalSection();

    /// @brief Destructor.
    ///
    /// Leaving the critical section. The packet thread pool instance will be
    /// started according to new configuration.
    virtual ~MultiThreadingCriticalSection();

private:

    /// @brief Class method stopping and joining all threads of the pool.
    ///
    /// Stop the packet thread pool if running.
    static void stopPktProcessing();

    /// @brief Class method (re)starting threads of the pool.
    ///
    /// Start the packet thread pool according to current configuration.
    static void startPktProcessing();
};

}  // namespace dhcp
}  // namespace isc

#endif // MULTI_THREADING_UTIL_H
