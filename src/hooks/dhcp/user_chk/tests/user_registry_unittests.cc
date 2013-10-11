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

#include <dhcp/hwaddr.h>
#include <exceptions/exceptions.h>
#include <user_registry.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;

namespace {

TEST(UserRegistry, constructor) {
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));
}

TEST(UserRegistry, userBasics) {
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    UserIdPtr id, id2;
    // Make user ids.
    ASSERT_NO_THROW(id.reset(new UserId(UserId::HW_ADDRESS, "01010101")));
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::HW_ADDRESS, "02020202")));

    UserPtr user, user2;
    // Verify that a blank user cannot be added.
    ASSERT_THROW(reg->addUser(user), isc::BadValue);

    // Make new users.
    ASSERT_NO_THROW(user.reset(new User(*id)));
    ASSERT_NO_THROW(user2.reset(new User(*id)));

    // Add first user.
    ASSERT_NO_THROW(reg->addUser(user));

    // Verify user added can be found.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(*id));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(*id, found_user->getUserId());

    // Verify user not added cannot be found.
    ASSERT_NO_THROW(found_user = reg->findUser(*id2));
    EXPECT_FALSE(found_user);

    // Verfiy user can no longer be found.
    ASSERT_NO_THROW(reg->removeUser(*id));
    ASSERT_NO_THROW(found_user = reg->findUser(*id));
    EXPECT_FALSE(found_user);
}

TEST(UserRegistry, findByHWAddr) {
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Make a user.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::HW_ADDRESS, "01010101")));

    // Verify user can be added.
    ASSERT_NO_THROW(reg->addUser(user));

    // Make a HWAddr instance using the same id value.
    isc::dhcp::HWAddr hwaddr(user->getUserId().getId(), 
                             isc::dhcp::HTYPE_ETHER);

    // Verify user can be found by HWAddr.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(hwaddr));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(user->getUserId(), found_user->getUserId());
}

TEST(UserRegistry, findByDUID) {
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Make a user.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, "01010101")));

    // Verify user can be added.
    ASSERT_NO_THROW(reg->addUser(user));

    // Make a HWAddr instance using the same id value.
    isc::dhcp::DUID duid(user->getUserId().getId());

    // Verify user can be found by HWAddr.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(duid));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(user->getUserId(), found_user->getUserId());
}

TEST(UserRegistry, findByClientId) {
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Make a user.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::CLIENT_ID, "01010101")));

    // Verify user can be added.
    ASSERT_NO_THROW(reg->addUser(user));

    // Make a HWAddr instance using the same id value.
    isc::dhcp::ClientId client_id(user->getUserId().getId());

    // Verify user can be found by HWAddr.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(client_id));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(user->getUserId(), found_user->getUserId());
}

} // end of anonymous namespace
