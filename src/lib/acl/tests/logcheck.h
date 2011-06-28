// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LOGCHECK_H
#define LOGCHECK_H

#include <gtest/gtest.h>
#include <acl/acl.h>
#include <cassert>

// This is not a public header, it is used only inside the tests.

namespace isc {
namespace acl {
namespace tests {

// This is arbitrary guess of size for the log. If it's too small for your
// test, just make it bigger.
const size_t LOG_SIZE = 10;

// This will remember which checks did run already.
struct Log {
    // The actual log cells, if i-th check did run
    mutable bool run[LOG_SIZE];
    Log() {
        // Nothing run yet
        for (size_t i(0); i < LOG_SIZE; ++ i) {
            run[i] = false;
        }
    }
    // Checks that the first amount of checks did run and the rest didn't.
    void checkFirst(size_t amount) const {
        ASSERT_LE(amount, LOG_SIZE) << "Wrong test: amount bigger than size "
            "of log";
        {
            SCOPED_TRACE("Checking that the first amount of checks did run");
            for (size_t i(0); i < amount; ++ i) {
                EXPECT_TRUE(run[i]) << "Check #" << i << " did not run.";
            }
        }

        {
            SCOPED_TRACE("Checking that the rest did not run");
            for (size_t i(amount); i < LOG_SIZE; ++ i) {
                EXPECT_FALSE(run[i]) << "Check #" << i << "did run.";
            }
        }
    }
};

// This returns true or false every time, no matter what is passed to it.
// But it logs that it did run.
class ConstCheck : public Check<Log> {
public:
    ConstCheck(bool accepts, size_t logNum) :
        logNum_(logNum),
        accepts_(accepts)
    {
        assert(logNum < LOG_SIZE); // If this fails, the LOG_SIZE is too small
    }
    virtual bool matches(const Log& log) const {
        /*
         * This is abuse of the context. It is designed to carry the
         * information to check, not to modify it. However, this is the
         * easiest way to do the test, so we go against the design.
         */
        log.run[logNum_] = true;
        return (accepts_);
    }
private:
    size_t logNum_;
    bool accepts_;
};

}
}
}

#endif

// Local Variables:
// mode: c++
// End:
