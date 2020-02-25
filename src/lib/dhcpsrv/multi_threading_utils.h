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

/// @brief Function stopping and joining all threads of the pool.
/// @throw isc::NotImplemented until is implemented.
void stopPktProcessing();

/// @brief Function (re)starting threads of the pool.
/// @throw isc::NotImplemented until is implemented.
void startPktProcessing();

/// @brief RAII class creating a critical section.
///
/// @note: the multi-threading mode MUST NOT be changed in the RAII
/// @c MultiThreadingCriticalSection body.
class MultiThreadingCriticalSection : public boost::noncopyable {
public:
    /// @brief Constructor.
    /// Entering the critical section.
    MultiThreadingCriticalSection();

    /// @brief Destructor.
    /// Leaving the critical section.
    virtual ~MultiThreadingCriticalSection();

    /// @brief Class method stopping and joining all threads of the pool.
    /// @throw isc::NotImplemented until is implemented.
    static void stopPktProcessing();

    /// @brief Class method (re)starting threads of the pool.
    /// @throw isc::NotImplemented until is implemented.
    static void startPktProcessing();
};

}  // namespace dhcp
}  // namespace isc

#endif // MULTI_THREADING_UTIL_H
