// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <test_data_files_config.h>
#include <user_file.h>

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

/// @brief Tests the UserFile constructor.
TEST(UserFile, construction) {
    // Verify that a UserFile with no file name is rejected.
    ASSERT_THROW(UserFile(""), UserFileError);

    // Verify that a UserFile with a non-blank file name is accepted.
    ASSERT_NO_THROW(UserFile("someName"));
}

/// @brief Tests opening and closing UserFile
TEST(UserFile, openFile) {
    UserFilePtr user_file;

    // Construct a user file that refers to a non existant file.
    ASSERT_NO_THROW(user_file.reset(new UserFile("NoSuchFile")));
    EXPECT_FALSE(user_file->isOpen());

    // Verify a non-existant file fails to open
    ASSERT_THROW(user_file->open(), UserFileError);
    EXPECT_FALSE(user_file->isOpen());

    // Construct a user file that should exist.
    ASSERT_NO_THROW(user_file.reset(new UserFile
                                   (testFilePath("test_users_1.txt"))));
    // File should not be open.
    EXPECT_FALSE(user_file->isOpen());

    // Verify that we can open it.
    ASSERT_NO_THROW(user_file->open());
    EXPECT_TRUE(user_file->isOpen());

    // Verify that we cannot open an already open file.
    ASSERT_THROW(user_file->open(), UserFileError);

    // Verifyt we can close it.
    ASSERT_NO_THROW(user_file->close());
    EXPECT_FALSE(user_file->isOpen());

    // Verify that we can reopen it.
    ASSERT_NO_THROW(user_file->open());
    EXPECT_TRUE(user_file->isOpen());
}


/// @brief Tests makeUser with invalid user strings
TEST(UserFile, makeUser) {
    const char* invalid_strs[]= {
        // Missinge type element.
        "{ \"id\" : \"01AC00F03344\" }",
        // Invalid id type string value.
        "{ \"type\" : \"BOGUS\", \"id\" : \"01AC00F03344\"}",
        // Non-string id type
        "{ \"type\" : 1, \"id\" : \"01AC00F03344\"}",
        // Missing id element.
        "{ \"type\" : \"HW_ADDR\" }",
        // Odd number of digits in id value.
        "{ \"type\" : \"HW_ADDR\", \"id\" : \"1AC00F03344\"}",
        // Invalid characters in id value.
        "{ \"type\" : \"HW_ADDR\", \"id\" : \"THIS IS BAD!\"}",
        // Empty id value.
        "{ \"type\" : \"HW_ADDR\", \"id\" : \"\"}",
        // Non-string id.
        "{ \"type\" : \"HW_ADDR\", \"id\" : 01AC00F03344 }",
        // Option with non-string value
        "{ \"type\" : \"HW_ADDR\", \"id\" : \"01AC00F03344\", \"opt\" : 4 }",
        NULL
        };

    // Create a UseFile to work with.
    UserFilePtr user_file;
    ASSERT_NO_THROW(user_file.reset(new UserFile("noFile")));

    // Iterate over the list of invalid user strings and verify
    // each one fails.
    const char** tmp = invalid_strs;;
    while (*tmp) {
        EXPECT_THROW(user_file->makeUser(*tmp), UserFileError)
                     << "Invalid str not caught: ["
                     <<  *tmp << "]" << std::endl;
        ++tmp;
    }
}

/// @brief Test reading from UserFile
TEST(UserFile, readFile) {
    UserFilePtr user_file;

    // Construct and then open a known file.
    ASSERT_NO_THROW(user_file.reset(new UserFile
                                    (testFilePath("test_users_1.txt"))));
    ASSERT_NO_THROW(user_file->open());
    EXPECT_TRUE(user_file->isOpen());

    // File should contain four valid users. Read and verify each.
    UserPtr user;
    int i = 0;
    do {
        ASSERT_NO_THROW(user = user_file->readNextUser());
        switch (i++) {
            case 0:
                EXPECT_EQ(UserId::HW_ADDRESS, user->getUserId().getType());
                EXPECT_EQ("01ac00f03344", user->getUserId().toText());
                EXPECT_EQ("true", user->getProperty("opt1"));
                break;
            case 1:
                // File entry should have colons in id.
                EXPECT_EQ(UserId::HW_ADDRESS, user->getUserId().getType());
                EXPECT_EQ("01ac00f03345", user->getUserId().toText());
                EXPECT_EQ("true", user->getProperty("opt1"));
                break;
            case 2:
                EXPECT_EQ(UserId::DUID, user->getUserId().getType());
                EXPECT_EQ("225060de0a0b", user->getUserId().toText());
                EXPECT_EQ("true", user->getProperty("opt1"));
                break;
            case 3:
                // File entry should have colons in id.
                EXPECT_EQ(UserId::DUID, user->getUserId().getType());
                EXPECT_EQ("225060de0a0c", user->getUserId().toText());
                EXPECT_EQ("true", user->getProperty("opt1"));
                break;
            default:
                // Third time around, we are at EOF User should be null.
                ASSERT_FALSE(user);
                break;
        }
    } while (user);


    ASSERT_NO_THROW(user_file->close());
}

} // end of anonymous namespace
