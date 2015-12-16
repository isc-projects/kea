// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/unittests/resource.h>

#include <gtest/gtest.h>

#include <sys/time.h>
#include <sys/resource.h>

namespace isc {
namespace util {
namespace unittests {

void
dontCreateCoreDumps() {
    const rlimit core_limit = {0, 0};

    EXPECT_EQ(setrlimit(RLIMIT_CORE, &core_limit), 0);
}

} // end of namespace unittests
} // end of namespace util
} // end of namespace isc
