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

#include <boost/shared_ptr.hpp>

#include "logcheck.h"

using namespace isc::acl;
using namespace isc::acl::tests;

namespace {

// Test version of the Acl class. It adds few methods to examine the protected
// data, but does not change the implementation.
class TestACL : public ACL<Log> {
public:
    TestACL() :
        ACL<Log>(DROP)
    {}
    // Check the stored default action there
    void checkDefaultAction(BasicAction ac) {
        EXPECT_EQ(getDefaultAction(), ac);
    }
};

// The test fixture. Contains some members so they don't need to be manually
// created each time and some convenience functions.
class ACLTest : public ::testing::Test {
public:
    ACLTest() :
        next_check_(0)
    {}
    TestACL acl_;
    Log log_;
    size_t next_check_;
    boost::shared_ptr<Check<Log> > getCheck(bool accepts) {
        return (boost::shared_ptr<Check<Log> >(new ConstCheck(accepts,
                                                              next_check_++)));
    }
};

/*
 * This tests the default action and that nothing is run if nothing is
 * inserted (it's hard to imagine otherwise though).
 *
 * We use the default ACL unchanged from the test class.
 */
TEST_F(ACLTest, emptyRule) {
    acl_.checkDefaultAction(DROP);
    EXPECT_EQ(DROP, acl_.execute(log_));
    // No test was run
    log_.checkFirst(0);
}

/*
 * This tests the default action in case no check matches.
 */
TEST_F(ACLTest, noMatch) {
    acl_.append(getCheck(false), ACCEPT);
    acl_.append(getCheck(false), REJECT);
    EXPECT_EQ(DROP, acl_.execute(log_));
    // The first two checks were actually run (and didn't match)
    log_.checkFirst(2);
}

/*
 * Checks that it takes the first matching check and returns the
 * value. Also checks that the others aren't run at all.
 */
TEST_F(ACLTest, firstMatch) {
    acl_.append(getCheck(false), ACCEPT);
    acl_.append(getCheck(true), REJECT);
    acl_.append(getCheck(true), ACCEPT);
    EXPECT_EQ(REJECT, acl_.execute(log_));
    log_.checkFirst(2);
}

}
