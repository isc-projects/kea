// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UTIL_UNITTESTS_RESOURCE_H
#define UTIL_UNITTESTS_RESOURCE_H 1

namespace isc {
namespace util {
namespace unittests {

/// Don't create core dumps.
///
/// This function sets the core size to 0, inhibiting the creation of
/// core dumps. It is meant to be used in testcases where EXPECT_DEATH
/// is used, where processes abort (and create cores in the process).
/// As a new process is forked to run EXPECT_DEATH tests, the rlimits of
/// the parent process that runs the other tests should be unaffected.
void dontCreateCoreDumps();

} // end of namespace unittests
} // end of namespace util
} // end of namespace isc

#endif // UTIL_UNITTESTS_RESOURCE_H

// Local Variables:
// mode: c++
// End:
