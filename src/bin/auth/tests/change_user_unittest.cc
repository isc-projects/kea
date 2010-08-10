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
#include <unistd.h>             // for getuid

#include <string>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <auth/common.h>
#include <auth/change_user.h>

using namespace std;

namespace {
TEST(ChangeUserTest, changeToTheSameUser) {
    const char* const my_username = getenv("USER");

    // normally the USER environment variable should be set to the name
    // of the local user running this test, but it's not always the case.
    if (my_username == NULL) {
        cerr << "Environment variable USER is undefined, skipping the test"
             << endl;
        return;
    }

    // changing to the run time user should succeed.
    EXPECT_NO_THROW(changeUser(my_username));
}

TEST(ChangeUserTest, changeToTheSameUserId) {
    // same as above, but using numeric user ID
    EXPECT_NO_THROW(changeUser(
                        (boost::lexical_cast<string>(getuid())).c_str()));
}

TEST(ChangeUserTest, badUID) {
    // -1 should be an invalid numeric UID, and (hopefully) shouldn't be
    // a valid textual username.
    EXPECT_THROW(changeUser("-1"), FatalError);
}

TEST(ChangeUserTest, promotionAttempt) {
    // change to root should fail unless the running user is a super user.
    if (getuid() == 0) {
        cerr << "Already a super user, skipping the test" << endl;
        return;
    }
    EXPECT_THROW(changeUser("root"), FatalError);
}
}
