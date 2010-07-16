// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <stdlib.h>

#include <string>

#include <gtest/gtest.h>

#include <auth/common.h>
#include <auth/change_user.h>

using namespace std;

namespace {
class ChangeUserTest : public ::testing::Test {
protected:
    // normally the USER environment variable should be set to the name
    // of the local user running this test.  If we encounter a case where
    // this doesn't hold, we'll need to add a prerequisite check in each
    // test.  For now we assume this is valid for simplicity.
    ChangeUserTest() : my_username(getenv("USER")) {}
    const string my_username;
};

TEST_F(ChangeUserTest, changeToTheSameUser) {
    // changing to the run time user should succeed.
    EXPECT_NO_THROW(changeUser(my_username.c_str()));
}

TEST_F(ChangeUserTest, badUID) {
    // -1 should be an invalid numeric UID, and (hopefully) shouldn't be
    // a valid textual username.
    EXPECT_THROW(changeUser("-1"), FatalError);
}

TEST_F(ChangeUserTest, promotionAttempt) {
    // change to root should fail unless the running user is a super user.

    if (my_username == "root") {
        cerr << "Already a super user, skipping the test" << endl;
        return;
    }
    EXPECT_THROW(changeUser("root"), FatalError);
}
}
