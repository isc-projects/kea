// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/hwaddr.h>
#include <exceptions/exceptions.h>
#include <user_registry.h>
#include <user_file.h>
#include <test_data_files_config.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace user_chk;

namespace {

/// @brief Convenience method for reliably building test file path names.
///
/// Function prefixes the given file name with a path to unit tests directory
/// so we can reliably find test data files.
///
/// @param name base file name of the test file
std::string testFilePath(const std::string& name) {
    return (std::string(USER_CHK_TEST_DIR) + "/" + name);
}

/// @brief Tests UserRegistry construction.
TEST(UserRegistry, constructor) {
    // Currently there is only the default constructor which does not throw.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));
}

/// @brief Tests mechanics of adding, finding, removing Users.
TEST(UserRegistry, userBasics) {
    // Create an empty registry.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Verify that a blank user cannot be added.
    UserPtr user;
    ASSERT_THROW(reg->addUser(user), UserRegistryError);

    // Make a new id and user.
    UserIdPtr id;
    ASSERT_NO_THROW(id.reset(new UserId(UserId::HW_ADDRESS, "01010101")));
    ASSERT_NO_THROW(user.reset(new User(*id)));

    // Verify that we can add a user.
    ASSERT_NO_THROW(reg->addUser(user));

    // Verify that the user can be found.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(*id));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(found_user->getUserId(), *id);

    // Verify that searching for a non-existant user returns empty user pointer.
    UserIdPtr id2;
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::HW_ADDRESS, "02020202")));
    ASSERT_NO_THROW(found_user = reg->findUser(*id2));
    EXPECT_FALSE(found_user);

    // Verify that the user can be deleted.
    ASSERT_NO_THROW(reg->removeUser(*id));
    ASSERT_NO_THROW(found_user = reg->findUser(*id));
    EXPECT_FALSE(found_user);
}

/// @brief Tests finding users by isc::dhcp::HWaddr instance.
TEST(UserRegistry, findByHWAddr) {
    // Create the registry.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Make a new user and add it.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::HW_ADDRESS, "01010101")));
    ASSERT_NO_THROW(reg->addUser(user));

    // Make a HWAddr instance using the same id value.
    isc::dhcp::HWAddr hwaddr(user->getUserId().getId(), isc::dhcp::HTYPE_ETHER);

    // Verify user can be found by HWAddr.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(hwaddr));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(found_user->getUserId(), user->getUserId());
}

/// @brief Tests finding users by isc::dhcp::DUID instance.
TEST(UserRegistry, findByDUID) {
    // Create the registry.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Make a new user and add it.
    UserPtr user;
    ASSERT_NO_THROW(user.reset(new User(UserId::DUID, "01010101")));
    ASSERT_NO_THROW(reg->addUser(user));

    // Make a DUID instance using the same id value.
    isc::dhcp::DUID duid(user->getUserId().getId());

    // Verify user can be found by DUID.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(duid));
    EXPECT_TRUE(found_user);
    EXPECT_EQ(found_user->getUserId(), user->getUserId());
}

/// @brief Tests mixing users of different types.
TEST(UserRegistry, oneOfEach) {
    // Create the registry.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Make user ids.
    UserIdPtr idh, idd;
    ASSERT_NO_THROW(idh.reset(new UserId(UserId::HW_ADDRESS, "01010101")));
    ASSERT_NO_THROW(idd.reset(new UserId(UserId::DUID, "03030303")));

    // Make and add HW_ADDRESS user.
    UserPtr user;
    user.reset(new User(*idh));
    ASSERT_NO_THROW(reg->addUser(user));

    // Make and add DUID user.
    user.reset(new User(*idd));
    ASSERT_NO_THROW(reg->addUser(user));

    // Verify we can find both.
    UserPtr found_user;
    ASSERT_NO_THROW(found_user = reg->findUser(*idh));
    ASSERT_NO_THROW(found_user = reg->findUser(*idd));
}

/// @brief Tests loading the registry from a file.
TEST(UserRegistry, refreshFromFile) {
    // Create the registry.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    UserDataSourcePtr user_file;

    // Verify that data source cannot be set to null source.
    ASSERT_THROW(reg->setSource(user_file), UserRegistryError);

    // Create the data source.
    ASSERT_NO_THROW(user_file.reset(new UserFile
                                    (testFilePath("test_users_1.txt"))));

    // Set the registry's data source and refresh the registry.
    ASSERT_NO_THROW(reg->setSource(user_file));
    ASSERT_NO_THROW(reg->refresh());

    // Verify we can find all the expected users.
    UserIdPtr id;
    ASSERT_NO_THROW(id.reset(new UserId(UserId::HW_ADDRESS, "01ac00f03344")));
    EXPECT_TRUE(reg->findUser(*id));

    ASSERT_NO_THROW(id.reset(new UserId(UserId::DUID, "225060de0a0b")));
    EXPECT_TRUE(reg->findUser(*id));
}

/// @brief Tests preservation of registry upon refresh failure.
TEST(UserRegistry, refreshFail) {
    // Create the registry.
    UserRegistryPtr reg;
    ASSERT_NO_THROW(reg.reset(new UserRegistry()));

    // Create the data source.
    UserDataSourcePtr user_file;
    ASSERT_NO_THROW(user_file.reset(new UserFile
                                    (testFilePath("test_users_1.txt"))));

    // Set the registry's data source and refresh the registry.
    ASSERT_NO_THROW(reg->setSource(user_file));
    ASSERT_NO_THROW(reg->refresh());

    // Make user ids of expected users.
    UserIdPtr id1, id2;
    ASSERT_NO_THROW(id1.reset(new UserId(UserId::HW_ADDRESS, "01ac00f03344")));
    ASSERT_NO_THROW(id2.reset(new UserId(UserId::DUID, "225060de0a0b")));

    // Verify we can find all the expected users.
    EXPECT_TRUE(reg->findUser(*id1));
    EXPECT_TRUE(reg->findUser(*id2));

    // Replace original data source with a new one containing an invalid entry.
    ASSERT_NO_THROW(user_file.reset(new UserFile
                                    (testFilePath("test_users_err.txt"))));
    ASSERT_NO_THROW(reg->setSource(user_file));

    // Refresh should throw due to invalid data.
    EXPECT_THROW(reg->refresh(), UserRegistryError);

    // Verify we can still find all the original users.
    EXPECT_TRUE(reg->findUser(*id1));
    EXPECT_TRUE(reg->findUser(*id2));
}

} // end of anonymous namespace
