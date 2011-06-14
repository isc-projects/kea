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

#include <gtest/gtest.h>
#include <acl/acl.h>
#include <cassert>

using namespace isc::acl;
using boost::shared_ptr;

namespace {

// This is arbitrary guess of size for the log. If it's too small for your
// test, just make it bigger.
const size_t LOG_SIZE = 10;

// This will remember which checks did run already.
struct Log {
    // The actual log cells, if i-th check did run
    bool run[LOG_SIZE];
    Log() {
        // Nothing run yet
        for (size_t i(0); i < LOG_SIZE; ++i) {
            run[i] = false;
        }
    }
    // Checks that the first amount of checks did run and the rest didn't.
    void checkFirst(size_t amount) const {
        ASSERT_LE(amount, LOG_SIZE) << "Wrong test: amount bigger than size "
            "of log";
        {
            SCOPED_TRACE("Checking that the first amount of checks did run");
            for (size_t i(0); i < amount; ++i) {
                EXPECT_TRUE(run[i]) << "Check #" << i << " did not run.";
            }
        }

        {
            SCOPED_TRACE("Checking that the rest did not run");
            for (size_t i(amount); i < LOG_SIZE; ++i) {
                EXPECT_FALSE(run[i]) << "Check #" << i << "did run.";
            }
        }
    }
};

// This returns true or false every time, no matter what is passed to it.
// But it logs that it did run.
class ConstCheck : public Check<Log*> {
public:
    ConstCheck(bool accepts, size_t log_num) :
        log_num_(log_num),
        accepts_(accepts)
    {
        assert(log_num < LOG_SIZE); // If this fails, the LOG_SIZE is too small
    }
    typedef Log* LPtr;
    virtual bool matches(const LPtr& log) const {
        log->run[log_num_] = true;
        return (accepts_);
    }
private:
    size_t log_num_;
    bool accepts_;
};

// Test version of the Acl class. It adds few methods to examine the protected
// data, but does not change the implementation.
class TestAcl : public Acl<Log*> {
public:
    TestAcl() :
        Acl(DROP)
    {}
    // Check the stored policy there
    void checkPolicy(Action ac) {
        EXPECT_EQ(policy_, ac);
    }
};

// The test fixture. Contains some members so they don't need to be manually
// created each time and some convenience functions.
class AclTest : public ::testing::Test {
public:
    AclTest() :
        next_check_(0)
    {}
    TestAcl acl_;
    Log log_;
    size_t next_check_;
    shared_ptr<Check<Log*> > getCheck(bool accepts) {
        return (shared_ptr<Check<Log*> >(new ConstCheck(accepts,
                                                        next_check_++)));
    }
};

/*
 * This tests the policy (default return value) and that nothing is run
 * if nothing is inserted (it's hard to imagine otherwise though).
 *
 * We use the default ACL unchanged from the test class.
 */
TEST_F(AclTest, emptyPolicy) {
    acl_.checkPolicy(DROP);
    EXPECT_EQ(DROP, acl_.execute(&log_));
    // No test was run
    log_.checkFirst(0);
}

/*
 * This tests the policy in case no check matches.
 */
TEST_F(AclTest, policy) {
    acl_.append(getCheck(false), ACCEPT);
    acl_.append(getCheck(false), REJECT);
    EXPECT_EQ(DROP, acl_.execute(&log_));
    // The first two checks were actually run (and didn't match)
    log_.checkFirst(2);
}

/*
 * Checks that it takes the first matching check and returns the
 * value. Also checks that the others aren't run at all.
 */
TEST_F(AclTest, check) {
    acl_.append(getCheck(false), ACCEPT);
    acl_.append(getCheck(true), REJECT);
    acl_.append(getCheck(true), ACCEPT);
    EXPECT_EQ(REJECT, acl_.execute(&log_));
    log_.checkFirst(2);
}

}
