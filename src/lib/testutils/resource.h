// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef __ISC_TESTUTILS_RESOURCE_H
#define __ISC_TESTUTILS_RESOURCE_H

namespace isc {
namespace testutils {

/// Don't create core dumps.
///
/// This function sets the core size to 0, inhibiting the creation of
/// core dumps. It is meant to be used in testcases where EXPECT_DEATH
/// is used, where processes abort (and create cores in the process).
/// As a new process is forked to run EXPECT_DEATH tests, the rlimits of
/// the parent process that runs the other tests should be unaffected.

void
dontCreateCoreDumps(void);

} // end of namespace testutils
} // end of namespace isc

#endif /* __ISC_TESTUTILS_RESOURCE_H */
