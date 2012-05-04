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

#include <sys/time.h>
#include <sys/resource.h>
#include <log/message_initializer.h>
#include <gtest/gtest.h>

using namespace isc::log;

// Declare a set of messages to go into the global dictionary.

namespace {
const char* values[] = {
    "GLOBAL1", "global message one",
    "GLOBAL2", "global message two",
    NULL
};
}

TEST(MessageInitializerTest2, MessageLoadTest) {
    // Load the maximum number of message arrays allowed.  Some arrays may
    // already have been loaded because of static initialization from modules
    // in libraries linked against the test program, hence the reason for the
    // loop starting from the value returned by getPendingCount() instead of 0.
    for (size_t i = MessageInitializer::getPendingCount();
         i < MessageInitializer::MAX_MESSAGE_ARRAYS; ++i) {
        MessageInitializer initializer1(values);
    }

    // Note: Not all systems have EXPECT_DEATH.  As it is a macro we can just
    // test for its presence and bypass the test if not available.
#ifdef EXPECT_DEATH
    // Adding one more should take us over the limit.
    EXPECT_DEATH({
        /* Set rlimits so that no coredumps are created. As a new
           process is forked to run this EXPECT_DEATH test, the rlimits
           of the parent process that runs the other tests should be
           unaffected. */
        rlimit core_limit;
        core_limit.rlim_cur = 0;
        core_limit.rlim_max = 0;
        EXPECT_EQ(setrlimit(RLIMIT_CORE, &core_limit), 0);

        MessageInitializer initializer2(values);
      }, ".*");
#endif
}
