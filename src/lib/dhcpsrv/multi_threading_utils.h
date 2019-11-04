// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_UTIL_H
#define MULTI_THREADING_UTIL_H

#include <boost/noncopyable.hpp>

namespace isc {
namespace dhcp {

/// @note: everything here MUST be used only from the main thread.
/// When called from a thread of the pool it can deadlock.

/// @brief Function stopping and joining all threads of the pool.
/// @throw isc::NotImplemented until is implemented.
void stop_pkt_processing();

/// @brief Function (re)starting threads of the pool.
/// @throw isc::NotImplemented until is implemented.
void start_pkt_processing();

/// @brief RAII class creating a critical section.
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
    static void stop_pkt_processing();

    /// @brief Class method (re)starting threads of the pool.
    /// @throw isc::NotImplemented until is implemented.
    static void start_pkt_processing();

private:
    /// @brief Local copy of the multi-threading mode.
    bool enabled_;
};

}
}
#endif // MULTI_THREADING_UTIL_H
