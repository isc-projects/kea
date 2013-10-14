// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <user.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;

namespace {

TEST(UserTest, construction) {
    std::string test_address("01FF02AC030B0709");

    UserIdPtr id;
    ASSERT_NO_THROW(id.reset(new UserId(UserId::HW_ADDRESS, test_address)));

    UserPtr user;
    // Verify construction from a UserId.
    ASSERT_NO_THROW(user.reset(new User(*id)));

    // Verify construction from a type and an address vector.
    ASSERT_NO_THROW(user.reset(new User(UserId::HW_ADDRESS, id->getId())));
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, id->getId())));
    ASSERT_NO_THROW(user.reset(new User(UserId::CLIENT_ID, id->getId())));

    // Verify construction from a type and an address string.
    ASSERT_NO_THROW(user.reset(new User(UserId::HW_ADDRESS, test_address)));
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, test_address)));
    ASSERT_NO_THROW(user.reset(new User(UserId::CLIENT_ID, test_address)));
}

TEST(UserTest, properties) {
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, "01020304050607")));

    std::string value = "";
    EXPECT_NO_THROW(user->setProperty("one","1"));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_EQ("1", value);

    EXPECT_NO_THROW(user->setProperty("one","1.0"));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_EQ("1.0", value);

    EXPECT_NO_THROW(user->delProperty("one"));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_TRUE(value.empty());

    EXPECT_THROW(user->setProperty("", "blah"), isc::BadValue);

    EXPECT_NO_THROW(user->setProperty("one", ""));
    EXPECT_NO_THROW(value = user->getProperty("one"));
    EXPECT_TRUE(value.empty());
}

} // end of anonymous namespace
