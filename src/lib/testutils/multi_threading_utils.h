// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_UTILS_H
#define MULTI_THREADING_UTILS_H

#include <util/multi_threading_mgr.h>

namespace isc {
namespace test {

/// @brief A RAII class which disables the multi threading on exit of scope.
///
/// Usually the multi threading is disabled by the fixture destructor or
/// TearDown but of course this works only when a fixture class is used.
class MultiThreadingTest {
public:

    /// @brief Constructor (set multi threading mode).
    ///
    /// @param mode The mode to use in the body. Defaults to true / enabled.
    MultiThreadingTest(bool mode = true) {
        isc::util::MultiThreadingMgr::instance().setMode(mode);
    }

    /// @brief Destructor (disable multi threading).
    ~MultiThreadingTest() {
        isc::util::MultiThreadingMgr::instance().setMode(false);
    }
};

} // end of isc::test namespace
} // end of isc namespace

#endif // MULTI_THREADING_UTILS_H
